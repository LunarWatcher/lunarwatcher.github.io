---
title: "Native accessibility APIs in Java Swing"
tags: ["java", "accessibility"]
published_date: 2026-01-18T19:32:39+01:00
---

While not enabled by default, Java Swing has support for accessibility APIs. Unfortunately, only Windows is supported by Java itself, but other operating systems are implemented by the different OSes themselves.

The flag is `-Djavax.accessibility.assistive_technologies=<provider>`, where some of the platform-specific providers are:

* **Linux/Gnome** (AT-SPI2): `org.GNOME.Accessibility.AtkWrapper`
    * Requires `java-atk-wrapper`: https://github.com/GNOME/java-atk-wrapper and a hack for adding the ATK library to the path: `sudo ln -s /usr/lib/x86_64-linux-gnu/jni/libatk-wrapper.so /usr/lib` - or sorting out the classpath so `libatk-wrapper.so` is in the path
    * Should work outside Gnome, for the record; I've run it headlessly in matchbox-window-manager in a bare minimum X11 CI environment with Xvfb. KDE [has a webdriver built in pyatspi2](https://github.com/KDE/selenium-webdriver-at-spi). It's unfortunately licensed under AGPL, but shows that KDE does work with AT-SPI2
* **Windows** (native shit): `com.sun.java.accessibility.AccessBridge`
    * Requires `%JRE_HOME%\bin\jabswitch -disable`
* **Crapple shitOS**: Not checked yet

Once enabled, the app can be tested using various testing tools. I was unable to find a solution that supports AT-SPI2[^1], so for my use, I hacked one together with pywinctl[^2], pyautogui[^3], and the adapter pattern to allow for other APIs to just be dropped into the testing framework. 

I may make an open-source testing framework based on this concept At Some Point:tm:, but I have no immediate use for it for my personal projects. The amount of testing frameworks using accessibility APIs is fairly high, but the amount that _also_ support AT-SPI2 on Linux is functionally non-existent[^4].

[^1]: KDE's promising-looking webdriver using appium is out of the question because it uses wayland, and it's licensed under AGPL, which alone is enough to exclude it from my use.
[^2]: Technically redundant since the windows it produces are incompatible with the windows AT-SPI2 uses, and AT-SPI2 still gives a chunk of the same functionality
[^3]: No longer maintained as far as I can tell, but it's so small that it could've been considered feature-complete if the author didn't leave a bunch of TODOs for future development
[^4]: Again exceluding KDE's webdriver, because AGPL is a cancer
