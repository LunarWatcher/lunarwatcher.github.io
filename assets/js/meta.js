---
---
// This does not work in local development because browsers refuse to do fetch calls to local files even when the files
// are local.
// There's a firefox `about:config` option to disable this (allegedly), and it crashed the tab. Nice.
fetch(
    "{{ site.prefix }}/_violet-meta.json"
)
    .then(body => body.json())
    .then(json => {
        document.getElementById("meta-violet-version").innerText = json["build"]["version"];
        document.getElementById("meta-violet-gen-time").innerText = json["build"]["time_ms"];

        document.getElementById("meta-violet-in-files").innerText = json["input"]["files"];
        document.getElementById("meta-violet-in-pages").innerText = json["input"]["pages"];

        document.getElementById("meta-violet-out-pages").innerText = json["output"]["pages"];
        document.getElementById("meta-violet-generated-at").innerText = new Date(
            json["build"]["started_at"]
        )
    });
