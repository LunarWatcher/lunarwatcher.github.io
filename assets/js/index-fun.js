document.getElementById("profile-pic")
    .addEventListener("click", (ev) => {
        if (ev.offsetY < 150) {
            document.getElementById("profile-pic-popover").togglePopover();
        }
    });

const dateFormatter = new Intl.DateTimeFormat([], {
    timeZone: "Europe/Oslo",
    hour12: false,
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
    timeZoneName: "longOffset"
});

setTimeout(() => {
    setInterval(() => {
        document.getElementById("current-time").innerText =
            dateFormatter.format(new Date());
    }, 1000);
},
    // Align the interval with each second actually flipping
    // (My OS taskbar has the time with seconds, so any drift greatly annoys me)
    1000 - new Date().getMilliseconds()
);
