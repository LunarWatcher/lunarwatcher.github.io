---
{
    "title": "Making big downloads resumable in firefox",
    "date": "2026-10-11T17:56:29+02:00",
    "last_modified": "2026-10-17T12:00:20+02:00",
    "type": "blog",
    "taxonomies": {
        "tags": ["firefox"]
    }
}
---

For whatever reason, Firefox 28 and newer (i.e. every modern version after like [2014](https://morgb.blogspot.com/2014/05/firefox-29-and-http-response-timeout.html)) ships with `network.http.response.timeout` set to 300 seconds. This seems to interfere with resuming big downloads (read: tens of gigs).

Setting `network.http.response.timeout` to `0` (or something very big) in `about:config` seems to make big downloads resumable. I don't understand why this works, but experimental testing supports it. This may or may not just generally affect flaky downloads that take a long time to finish, which at least for my general use-case only includes big downloads. For now at least.

Note that this assumes the server supports resumable downloads; if it doesn't, no settings in firefox or any other browser are going to help. However, the problem this fixes is firefox being unable to resume a resumable download on error. The test case for this was the SE data dump (the full one released earlier this month), as well as the SO dump in particular, which are 90GiB and ~60GiB respectively. I don't entirely know if this is the case, but it experimentally looks like resumable downloads in firefox rely on connection timeouts rather than the `.part` files they download. Firefox will happily ignore an existing `.part` without this option, and I do not understand why.

Resumable downloads in firefox generally appear to be fairly unstable though. This has been a known problem in some form since [as far back as 2005](https://forums.mozillazine.org/viewtopic.php?t=238764). I also found that there's [a manual `.part` shuffle to make firefox actually resume downloads](https://superuser.com/a/1103144) across sessions, or presumably FF deciding to ignore the `.part` in a running session because of the timeout option, but I'm not doing that shit. As a non-firefox workaround, using `wget -c -O "$filename" "$url"` also works, and wget overall appears to be fairly stable. Using wget for resuming is also much easier if the URL changes, which the SO data dump URLs may or may not do depending on whether or not SE has reset the expiration time of the URL for any given data dump. The only way to get that with Firefox is the `.part` shuffle, and fuck that.

<p><sub>I have not attempted to confirm any of this with FF's source code, because I have no clue where to look.</sub></p>

