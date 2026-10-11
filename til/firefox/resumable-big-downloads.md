---
{
    "title": "Making big downloads resumable in firefox",
    "date": "2026-10-11T17:56:29+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["firefox"]
    }
}
---

For whatever reason, Firefox 28 and newer (i.e. every modern version after like [2014](https://morgb.blogspot.com/2014/05/firefox-29-and-http-response-timeout.html)) ships with `network.http.response.timeout` set to 300 seconds. This seems to interfere with resuming big downloads, as well as the general stability of big downloads.

Setting `network.http.response.timeout` to `0` (or something very big) in `about:config` seems to make big downloads both resumable and at least a little more stable. I don't understand why this works, but experimental testing supports it.

Note that this assumes the server supports resumable downloads; if it doesn't, no settings in firefox or any other browser are going to help. However, the problem this fixes is firefox being unable to resume a resumable download on error. I don't entirely know if this is the case, but it experimentally looks like resumable downloads in firefox rely on connection timeouts rather than the `.part` files they download. Firefox will happily ignore an existing `.part` without this option, and I do not understand why.

Resumable downloads in firefox generally appear to be fairly unstable though. This has been a known problem in some form since [as far back as 2005](https://forums.mozillazine.org/viewtopic.php?t=238764). I also found that there's [a manual `.part` shuffle to make firefox actually resume downloads](https://superuser.com/a/1103144), but I'm not doing that shit. As a non-firefox workaround, using `wget -c -O "$filename" "$url"` also works, and wget overall appears to be fairly stable.

I do also suspect firefox does some hidden retries if it can before it considers the download to have failed - from some experimental testing, it does appear that this is at least partly related to `network.http.response.timeout`, and that exceeding the timeout interferes with this process.

I have not attempted to confirm any of this with FF's source code, because I have no clue where to look.

