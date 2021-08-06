
function openSidenav() {
    document.getElementById("sidenav").style.width = "100%";
}

function closeSidenav() {
    document.getElementById("sidenav").style.width = "0%";
}

window.onload=function() {
    let greetings = [
        "Hiya. Whatcha doing there? :eyes:",
        "Trans rights!",
        "Press Alt-F4 to continue.",
        "Roses are red,\nViolets are blue,\nThere's nothing to see here,\nExcept my shitty \"poetry\"",
        "Self-destruct initiated",
        "Don't h4xx0r me @ 127.0.0.1, thanks in advance"
    ];
    const random = Math.floor(Math.random() * greetings.length);
    console.log(random, greetings[random]);
};
