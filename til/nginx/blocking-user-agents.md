---
title: Blocking user agents with nginx
published_date: 2025-02-27 13:22:51 +0100
tags:
- nginx
---

My server has been attacked repeatedly by censys and some company called Expanse, from enough IPs that I need to look into range banning their networks. Doing so is logistically annoying, so obviously, the sane kneejerk response until then is to ban their user agents in nginx with a custom message out of spite.

It's fairly easy to do with a map and an if statement:

```nginx
http {

    map $http_user_agent $blocked_ua {
        default 0;
        # Various organisations that attack servers, but seem to get away with doing so for some reason.
        # This list is not synced with my currently used list
        "~*censys" 1;
        "~*paloaltonetworks.com" 1;
    }

    server {
        # ... 
        if ($blocked_ua) {
            return 403 "Fuck off";
        }
    }

}
```

This needs to be configured on a per-`server` basis, because reasons.

> [!NOTE]
> This does not stack with `deny` blocks. The main problem with this is that if the `server` has a `deny all` with explicit `allow [localhost IPs]`, the UA ban will not take effect, because the `deny` appears to always take precedence over `if` statements regardless of order in the code. To be fair, this does make sense.
