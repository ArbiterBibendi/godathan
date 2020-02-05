# Godathan

Discord Bot

Commands:
```
-send 
    Usage: -send ChannelID Message 
    Sends a message to a text channel
    E.g. "-send 673944456940093451 This is an example message"

-yt
    Usage: -yt \[format\] LINK
    Downloads a youtube video into the discord chat (Must be smaller than 8MB)
    Formats: mp3, mp4
```
## Getting Started

### Prerequisites

What things you need to install the software

```
CMake
Make
Curl
```

### Installing

Create a Discord Bot Application [Here](https://discordapp.com/developers/docs/intro)
Take note of it's API Token

To install godathan:
```
git clone https://github.com/ArbiterBibendi/godathan
cd godathan
```
Change the API_TOKEN definition from API_TOKEN_GOES_HERE to your bot's API Token
```
cd build
cmake ..
make
```

The executable will be placed in godathan/bin
Invite your bot to your server
Run the executable


## Authors

* **Drake Scott** - [ArbiterBibendi](https://github.com/ArbiterBibendi)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thank you to [yourWaifu](https://github.com/yourWaifu) for the Discord API Wrapper for C++
* And thank you to all of the contributors of [youtuble-dl](https://github.com/ytdl-org/youtube-dl) for 
  making and maintaining such an amazing tool.
