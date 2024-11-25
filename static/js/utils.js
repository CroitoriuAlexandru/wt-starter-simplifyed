window.addEventListener("keydown", function(e) {
    if(e.altKey && ["ArrowUp","ArrowDown","ArrowLeft","ArrowRight"].indexOf(e.code) > -1) {
        e.preventDefault();
    }
}, false);

// document.addEventListener('contextmenu', event => {
//     event.preventDefault();
// });