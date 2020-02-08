# Godathan

## A Discord Bot

**Commands:**
```
-send 
    Usage: -send ChannelID Message 
    Sends a message to a text channel
    E.g. "-send 673944456940093451 This is an example message"

-yt
    Usage: -yt [format] VIDEO (Name or Link)
    Downloads a youtube video into the discord chat (Must be smaller than 8MB)
    Formats: mp3, mp4
```
## Getting Started

### Prerequisites

What things you need to install the software

```
CMake
Make
libcurl4-openssl-dev
```

### Installing

Create a Discord Bot Application [Here](https://discordapp.com/developers/docs/intro)
Take note of it's API Token

To install godathan:

Clone the repo
```
git clone https://github.com/ArbiterBibendi/godathan
cd godathan
```
Change the the API Token in the APITOKEN.example file from YOUR_API_TOKEN_HERE to your bot's API Token
then rename APITOKEN.example to APITOKEN
```
echo "{YOUR_API_TOKEN}" > APITOKEN.example
mv APITOKEN.example APITOKEN
```
Move to the build directory and build the project
```
cd build
cmake ..
make
```

The executable will be placed in godathan/bin
Now Invite your bot to your server and run the executable


## Authors

* **Drake Scott** - [ArbiterBibendi](https://github.com/ArbiterBibendi)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thank you to [yourWaifu](https://github.com/yourWaifu) for the Discord API Wrapper for C++
* And thank you to all of the contributors of [youtuble-dl](https://github.com/ytdl-org/youtube-dl) for 
  making and maintaining such an amazing tool.
