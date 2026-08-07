function toggleNav() {
    document.getElementById("navigation").classList.toggle("visible");
}

hljs.addPlugin({
    "after:highlightElement": ({ el, result, _ }) =>  {
        // This is used to display the language, but it might be a better idea to add a proper element.
        el.setAttribute("data-language", result.language)
    },
});

function signalCopied(el) {
    const text = el.text;
    el.text = "Copied!";
    setTimeout(() => {
        el.text = text;
    }, 1500);
}

hljs.highlightAll();

document.querySelectorAll("h1,h2,h3,h4,h5,h6").forEach(el => {
    if (!el.id) {
        return;
    }
    const anchor = document.createElement("a");
    anchor.text = "#";
    anchor.classList += "header-backlink";
    anchor.href = "#" + el.id;
    anchor.onclick = (ev) => {
        ev.preventDefault();
        // TODO: There has to be a better way to do this
        navigator.clipboard.writeText(
            window.location.protocol + "//"
            + window.location.pathname + "#" + el.id
        );
        signalCopied(ev.target);
    }
    el.prepend(anchor);
});

document.querySelectorAll(
    "pre > code"
).forEach(el => {
    el.innerHTML = el.innerHTML
        .replace(
            /^(.*)$/gm,
            '<span class="hljs-line-shim">$1</span>'
        );
})

