function openSidenav() {
    document.getElementById("sidenav").style.width = "100%";
    document.getElementsByTagName("body")[0].classList.add("sidenav-open");
}

function closeSidenav() {
    document.getElementById("sidenav").style.width = "0%";
    document.getElementsByTagName("body")[0].classList.remove("sidenav-open");
}

function rand(arr) {
    return arr[Math.floor(Math.random() * arr.length)]
}

function uwu() {
    document.getElementById("uwu").text = "This was not the best use of time. Now you get to suffer with me :p";
    let emojis = [
        "owo", "OwO",
        "uwu", "UwU",
        ":3", "x3",
        "rawr x3",
        "howls uwu",
        "growl (╬ Ò ‸ Ó)",
        "(* ^ ω ^)",
        "I like trains"
    ];

    let body = document.body.getElementsByTagName("main")[0];
    let queue = [...body.children];
    while (queue.length > 0) {
        let element = queue.shift();
        if (element.children.length > 0) {
            queue.push(...element.children);
        }
        [...element.childNodes].filter((node) => {
            return (node.nodeType === Node.TEXT_NODE && node.nodeValue.trim() !== "");
        }).forEach((node) => {
            node.textContent = node.textContent.replace(/[lr]/ig, (str) => { 
                return str[0].toLowerCase() == str[0] ? "w" : "W";
            }).replace(/[.!?]/gi, (str) => {
                let char = str[0];
                if (Math.random() > 0.7) {
                    return char + " " + rand(emojis);
                }
                return char;
            });
        });
    }
    console.log(body);

}

function copyLink(ev, link) {
    ev.preventDefault();
    navigator.clipboard.writeText(link);

    ev.target.innerHTML = "Copied link!";
    setTimeout(() => {
        ev.target.innerHTML = "Share";
    }, 3000);

    return false;
}

window.onload=function() {
    let greetings = [
        "Hiya. Whatcha doing there? :eyes:",
        "Trans rights!",
        "Press Alt-F4 to continue.",
        "Roses are red,\nViolets are blue,\nThere's nothing to see here,\nExcept my shitty \"poetry\"",
        "Self-destruct initiated",
        "Don't h4xx0r me @ 127.0.0.1, thanks in advance",
        "Secret free file storage using youtube, remove message before committing: https://www.youtube.com/watch?v=yRKh34Ofg50"
    ];
    console.log(rand(greetings));
};
