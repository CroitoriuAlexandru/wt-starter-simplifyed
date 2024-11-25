#include "100-Utils/AwsConnect.h"
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/DeleteObjectRequest.h>

#include <fstream>

using namespace Aws;
using namespace Aws::Auth;
AwsConnect::AwsConnect()
{
}

void AwsConnect::displayBuckets()
{
    Aws::SDKOptions options;
    // Optionally change the log level for debugging.
    options.loggingOptions.logLevel = Utils::Logging::LogLevel::Debug;
    Aws::InitAPI(options); // Should only be called once.
    int result = 0;
    {
        Aws::Client::ClientConfiguration clientConfig;
        // Optional: Set to the AWS Region (overrides config file).
        // clientConfig.region = "us-east-1";

        // You don't normally have to test that you are authenticated. But the S3 service permits anonymous requests, thus the s3Client will return "success" and 0 buckets even if you are unauthenticated, which can be confusing to a new user.
        auto provider = Aws::MakeShared<DefaultAWSCredentialsProviderChain>("alloc-tag");
        auto creds = provider->GetAWSCredentials();
        if (creds.IsEmpty())
        {
            std::cerr << "Failed authentication" << std::endl;
        }

        Aws::S3::S3Client s3Client(clientConfig);
        auto outcome = s3Client.ListBuckets();

        if (!outcome.IsSuccess())
        {
            std::cerr << "Failed with error: " << outcome.GetError() << std::endl;
            result = 1;
        }
        else
        {
            std::cout << "Found " << outcome.GetResult().GetBuckets().size()
                      << " buckets\n";
            for (auto &bucket : outcome.GetResult().GetBuckets())
            {
                std::cout << bucket.GetName() << std::endl;
            }
        }
    }

    Aws::ShutdownAPI(options); // Should only be called once.
}

std::string AwsConnect::sendFile(std::string file_path, std::string aws_file_path)
{
    std::string return_url = "";
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Debug;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = "aipro-storage";
        const Aws::String object_name = aws_file_path;
        const Aws::String file_name = file_path; // Adjusted file path

        Aws::Client::ClientConfiguration clientConfig;
        clientConfig.region = Aws::Region::EU_NORTH_1;
        // clientConfig.endpointOverride = endpoint;
        // clientConfig.verifySSL = false; // Disable SSL certificate verification

        Aws::S3::S3Client s3_client(clientConfig);

        // Read the image file into a buffer
        std::ifstream input_file(file_name.c_str(), std::ios::binary);
        if (!input_file)
        {
            std::cerr << "Failed to open file " << file_name << std::endl;
            Aws::ShutdownAPI(options);
            return return_url;
        }

        Aws::StringStream buffer;
        buffer << input_file.rdbuf();
        Aws::String image_data = buffer.str();

        // Create a PutObjectRequest
        Aws::S3::Model::PutObjectRequest object_request;
        object_request.SetBucket(bucket_name);
        object_request.SetKey(object_name);

        // Set the image data as the body of the request
        auto data = Aws::MakeShared<Aws::StringStream>("");
        *data << image_data;
        object_request.SetBody(data);

        // Put the object into the bucket
        auto put_object_outcome = s3_client.PutObject(object_request);

        if (put_object_outcome.IsSuccess())
        {
            std::cout << "Successfully uploaded " << object_name << " to " << bucket_name << std::endl;
            std::cout << "ETag: " << put_object_outcome.GetResult().GetETag() << std::endl;
            std::cout << "File URL: https://" << bucket_name << ".s3." << clientConfig.region << ".amazonaws.com/" << object_name << std::endl;
            return_url = "https://" + bucket_name + ".s3." + clientConfig.region + ".amazonaws.com/" + object_name;
        }
        else
        {
            std::cerr << "Failed to upload " << object_name << " to " << bucket_name << ": "
                      << put_object_outcome.GetError().GetMessage() << std::endl;
        }
    }
    Aws::ShutdownAPI(options);
    return return_url;
}

bool AwsConnect::deleteFile(std::string aws_file_path)
{
    bool success = false;
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Debug;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = "aipro-storage";
        const Aws::String object_name = aws_file_path.c_str();

        Aws::Client::ClientConfiguration clientConfig;
        clientConfig.region = Aws::Region::EU_NORTH_1;
        Aws::S3::S3Client s3_client(clientConfig);

        Aws::S3::Model::DeleteObjectRequest object_request;
        object_request.SetBucket(bucket_name);
        object_request.SetKey(object_name);

        std::cout << "Attempting to delete object: " << object_name << " from bucket: " << bucket_name << std::endl;

        auto delete_object_outcome = s3_client.DeleteObject(object_request);

        if (delete_object_outcome.IsSuccess())
        {
            std::cout << "Successfully deleted " << object_name << " from " << bucket_name << std::endl;
            success = true;
        }
        else
        {
            std::cerr << "Failed to delete " << object_name << " from " << bucket_name << ": "
                      << delete_object_outcome.GetError().GetMessage() << std::endl;
        }
    }
    Aws::ShutdownAPI(options);
    return success;
}