# chromietabs
[![Build Status](https://travis-ci.org/loganek/chromietabs.svg?branch=master)](https://travis-ci.org/loganek/chromietabs)

Lightweight library for getting information about open/active tabs in Google Chrome and Chromium web browser

## Example
Example below demonstrates how to print all open tabs in the Google Chrome browser.

```c++
auto session_path = ChromieTabs::PathUtils::get_current_session_path(
                                              ChromieTabs::BrowserType::GOOGLE_CHROME);
ChromieTabs::SessionAnalyzer analyzer{ChromieTabs::SessionReader(session_path)};

std::cout << "Tabs:" << std::endl;
for (auto wnd_id : analyzer.get_window_ids())
{
    for (auto url : analyzer.get_window_urls(wnd_id))
    {
        std::cout << "   [Window " << wnd_id << "] Url: " << url << std::endl;
    }
}
```
Full example can be found here: [chromietabs-example](https://github.com/loganek/chromietabs/blob/master/example/main.cc)

## Build
1. Download the sources:

  a) latest git-master version:
   ```shell
   $ git clone https://github.com/loganek/chromietabs.git
   $ cd chromietabs
   ```
  b) latest release: [sources](https://github.com/loganek/chromietabs/releases) 

2. Compile the project
```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Documentation
Documentation for the latest version of the library can be found here: [master documentation](https://loganek.github.io/chromietabs/master/index.html).
Documentation for all available releases can be found here: [documentation](https://loganek.github.io/chromietabs/index.html).

## Contributing

Please fork the parent repository and contribute back using [pull requests](https://github.com/loganek/chromietabs/pulls). Features can be requested using [issues](https://github.com/loganek/chromietabs/issues). All code, comments, and critiques are greatly appreciated.

## Licensing
This project is developed under MIT license. See [LICENSE](https://github.com/loganek/chromietabs/blob/master/LICENSE) file for more details.
