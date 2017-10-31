<p align="center">
  <img width="342" src="https://raw.githubusercontent.com/ramirezd42/node-audio/master/logo.png">
</p>

[![npm version](https://badge.fury.io/js/node-audio.svg)](https://badge.fury.io/js/node-audio)

## What Is It?
**node-audio** is a graph-based audio processing library for Node.Js. It's very similar to the web-audio api. In fact in its current iteration it is little more than a binding for [LabSound](https://github.com/LabSound/LabSound) with some sugar on top!

The eventual goal of this project is to expand upon the possibilites offered by the Web Audio API for Node.js based platforms by making it easier to develop custom AudioNode types to suit your specific needs.

## WARNING!!!: 
This library is in an extremely experimental state. Large portions of functionally have yet to be implemented and it is currently only buildable for MacOSX. However, since everything is built with cross-platform libraries (namely [Boost](http://www.boost.org/), [LabSound](http://labsound.io) and [JUCE](https://www.juce.com/), supporting other operating systems shouldn't be too difficult if there's interest. That said...

## How can I help?
If you find **node-audio** helpful or want to help get it to a point where you think it COULD be helpful, there's a couple of ways you can contribute:

### Submit a PR:
Missing something you need to make this a viable tool for your use case? Submit a PR! 

### Create an issue
Need something, but don't have to time to contribute or aren't sure how? Open up an issue, I'd love to talk about it!

## What do we have so far?
### Graph API
Currently only a small subset of the web-audio-api is available. In lieue of api documentation for the time being you can check out the `src/module.cc` file to see what bindings are being made available.

### PluginNode
The only custom node type available right now is a "PluginNode". This can be used to instantiate an audio plugin and connect it to the graph as you would any other node. It currently supports only VST3 plugins, but the host process is built with JUCE so adding support for other formats like VST and AudioUnit shouldn't be too much work.

## What's Next
The next things I plan to tackle are: 

### Get closer to feature compatability with current web-audio-api
I think now that the foundation is laid this is more or less busy work. One of those things that's hard to justify until you need to use a certain piece of the api that's not available. PRs especially welcome here!

### Develop some means of support for developing and packaging custom nodes as npm packages.
I would really like to get to the point where developers can create custom node types that are `npm installed` as a dependency in a project using **node-audio**. I really want to get the plugin node out into a separate repo as well since it has some pretty heavy dependencies that ideally wouldn't be required by **node-audio** project itself

---

## Installation

Installation can be done via npm. Warning: this currently takes a LONG time to build!
```
> npm install --save node-audio
```
---
## Usage Examples
The example below will play back an audio file, and manipulate the audio via a VST3 plugin a pan node and a gain node:

```javascript
const { NodeAudio, StereoPannerNode, GainNode, SoundBuffer, PluginNode } = require('node-audio')

const ctx = NodeAudio.makeAudioContext()

const panNode = new StereoPannerNode(ctx.sampleRate())
panNode.pan().setValue(0)

const gainNode = new GainNode(ctx.sampleRate())
gainNode.gain().setValue(0.5)

const pluginNode = new PluginNode('/Path/to/plugin.vst3', ctx.sampleRate())

gainNode.connect(ctx, panNode, 0, 0)
panNode.connect(ctx, pluginNode, 0, 0)
pluginNode.connect(ctx, ctx.destination(), 0, 0)

const buffer = new SoundBuffer('/Path/to/audiofile.wav', ctx.sampleRate())
buffer.playOnNode(ctx, gainNode, 0)

while(true){}
```
