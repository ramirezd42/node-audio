const { NodeAudio, StereoPannerNode, GainNode } = require('./index.js')

const ctx = NodeAudio.makeAudioContext()
const input = NodeAudio.makeHardwareSourceNode(ctx)

const panNode = new StereoPannerNode(ctx.sampleRate())
panNode.pan().setValue(1)

const gainNode = new GainNode(ctx.sampleRate())
gainNode.gain().setValue(0.01)

input.connect(ctx, gainNode, 0, 0)
gainNode.connect(ctx, panNode, 0, 0)
panNode.connect(ctx, ctx.destination(), 0, 0)

while(true){}