document.getElementById("profile-pic")
    .addEventListener("click", (ev) => {
        if (ev.offsetY < 150) {
            alert("Headpats? 🥺")
        }
    });
