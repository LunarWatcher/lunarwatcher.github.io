---
title: GPG keys
---

# GPG keys

Starting July 4th 2020, I'll be signing my commit messages using [rsa4096/bb69e2fdf3828ca204c9260fd12a30317208673e](https://keyserver.ubuntu.com/pks/lookup?search=0xD12A30317208673E&fingerprint=on&op=index). Additionally, this key will be used whereever there's a need for a signature, provided it's possible.

These signatures are made with a public subkey with the fingerprint BB69 E2FD F382 8CA2 04C9 260F D12A 3031 7208 673E. You can pull this key with:
```

```

---

Cryptographic proof:

```json
{
    "date": "04.07.2020 18:22:00Z (ish)",
    "githubUsername": "LunarWatcher",
    "iDunno": "I actually have no idea what else to put in here, or if this in itself is overkill",
    "signedFor": "https://lunarwatcher.github.io/crypto.html"
}
```

Signed with BB69 E2FD F382 8CA2 04C9 260F D12A 3031 7208 673E, the object above yields the signature:

```
-----BEGIN PGP MESSAGE-----

owGbwMvMwMV4UcvAsIgj3Y5xLSNLEkdBUX5+ml5uSjzDSd5qLgUgUEpJLElVslJQ
MjDRMzDXMzIwMlAwtLAyMrIyMIhS0MgsztBU0oGoTM8syShNCi1OLcpLzAXr8SnN
SywKTyxJzkgtgqnKdCnNy8sHyXoqJCaXlCbm5FQqZCSWpSrk5StkpqQmKpRnJJYo
pOYUpyqU5CsUlJYoZOYpAA1I1VHIL1LITFMoycgsBolllhSn5qQpADn5ZalF2Zk5
OTA7ijPT81JT3PKLQNZklJQUFFvp6+eAHFMOcYwexK16mfn6yUWVBSX5ehkluTlK
XLVcnUzGLAyMXAyyYoosuzMf/f3c1LOI5aQaPyycWJlAYcPAxSkAEwl5wf9Pp6rD
/u8SvxesrWErnsu+6Hr24O5m2a86ZjGTHc3/c/U3HpdqPTyre/+FQCf5p9NYnU9a
b/kvcUziBntAp8JzwdeMrjfKz6+xXuP5qertsxspqqeKNv2Qnq9/+kLpg1Mt3nNv
3zRZz1nu572Bu+uoQItG5rN1r9xfLkzYsphvv99WsTCDnBu804XUTkj8frF7f8az
ko9JEm/rtrMcnh4hIBffOvOO4Kv614+rM97ndhx/trz39tu3bw0Pf+Z/IFqj/znF
J+bnn7C1M8W7hHd9+SXIelcg91xOkM+OhkJF/q+T8q21jYUkprnNmu+/OVg6cqa/
yKTVi6WepS27mmN90DTv91mZ+X8vvdtwzTrryrcSnuq8A/qbfte3vBG0/rwuIE1z
85JQXjMxLnWjTd81Va5+3vdUZv75hUtqCtRvMVZ8OLfsrqHg1Q8vNJbv91vL/olz
Se21thOTHwc/824TfTm1br3Pzzq/GfzWFy4bp5dNXbiZvdOvz+FLBX/dLjYD0QMu
fcrfv/Z3XDdSCRQwqrkpopPXV5Sm6bPem833zJPdmbu/2rvn/P70WP/AggnN4rt9
Fi/KenTc5oz7yeDkRUeszu7O0fC64mEnfDWAQ0JTfx9TE+ezy75HZbwPKLgfEwv5
dLYkTEv09PVlmhelnuypOHfATdPg0r2KrbdEjPiMOl+d2xhl9MHw3C6Xf32Rxr0m
Z12TsqVz1pvNAgA=
=2/Of
-----END PGP MESSAGE-----
```

(can be verified with `gpg --decrypt test.sig`, which displays the content as well, or `gpg --verify test.sig` to only show the signature)

This page may be modified if one or more of my keys become compromised, and I'm forced to revoke the key(s). In the event of that, the standard GPG revocation system will be used as well.
