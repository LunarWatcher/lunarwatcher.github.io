---
{
    "title": "Misc gateway",
    "hidden": true
}
---

This page contains links to pages that didn't fit in anywhere else on the website, at least for now.

<ul>
{% for p in listPages(page, ".") %}
    <li><a href="{{ site.prefix }}/{{ p.url }}">{{ p.title }}</a></li>
{% endfor %}
</ul>
