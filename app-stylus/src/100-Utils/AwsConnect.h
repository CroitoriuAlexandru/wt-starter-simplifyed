#pragma once
#include <iostream>

class AwsConnect
{
public:
    AwsConnect();

    void displayBuckets();
    std::string sendFile(std::string file_path, std::string aws_file_path);
    bool deleteFile(std::string aws_file_path);

private:
};