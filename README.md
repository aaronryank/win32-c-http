# win32-c-http
Simple C HTTP server for Windows

Works fine for one client connection, serves full HTML/CSS/JS.

TODO: (looking for forks and PRs, as I no longer actively maintain this)

- Allow multiple connections (links: [`CreateThread`](https://msdn.microsoft.com/en-us/library/windows/desktop/ms682453(v=vs.85).aspx), [`CreateProcess`](https://msdn.microsoft.com/en-us/library/windows/desktop/ms682425(v=vs.85).aspx), [Creating Threads](https://msdn.microsoft.com/en-us/library/windows/desktop/ms682516(v=vs.85).aspx) and [various](http://stackoverflow.com/q/4768294/6850771) [StackOverflow](http://stackoverflow.com/q/8446757/6850771) [posts](http://stackoverflow.com/q/331536/6850771))
- Allow connections from external sources (e.g. not on the same router)
