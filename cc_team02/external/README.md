## Content

This folder contains external, third-party source code.

- [log.c](https://github.com/rxi/log.c) by [rxi](https://github.com/rxi) (see [README](https://github.com/rxi/log.c/blob/master/README.md)/[LICENSE](https://github.com/rxi/log.c/blob/master/LICENSE))
- [map.c](https://github.com/rxi/map) by [rxi](https://github.com/rxi) (see [README](https://github.com/rxi/map/blob/master/README.md)/[LICENSE](https://github.com/rxi/map/blob/master/LICENSE))

### Custom modifications

The changes made to the external libraries are listed here as well as in the comments within the (modified) source code.

[log.c](log/src/log.c):

- Print out also milliseconds
- Show only file-name, [not full-path](https://github.com/rxi/log.c/pull/2/commits/7e28989e55496530e36d94bdc1441b338442bd68) in log
- Logging-format slightly changed (logging info between '[' and ']')