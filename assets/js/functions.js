function openSidenav() {
    document.getElementById("sidenav").style.width = "100%";
}

function closeSidenav() {
    document.getElementById("sidenav").style.width = "0%";
}

function rand(arr) {
    return arr[Math.floor(Math.random() * arr.length)]
}

function uwu() {
    document.getElementById("uwu").text = "OWO!!";
    let emojis = [
        "owo", "OwO",
        "uwu", "UwU",
        ":3", "x3",
        "rawr x3",
        "howls uwu",
        "growl (╬ Ò ‸ Ó)",
        "(* ^ ω ^)"
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

window.onload=function() {
    let greetings = [
        "Hiya. Whatcha doing there? :eyes:",
        "Trans rights!",
        "Press Alt-F4 to continue.",
        "Roses are red,\nViolets are blue,\nThere's nothing to see here,\nExcept my shitty \"poetry\"",
        "Self-destruct initiated",
        "Don't h4xx0r me @ 127.0.0.1, thanks in advance"
    ];
    console.log(rand(greetings));
};
