const { NodeAudio, StereoPannerNode, GainNode, SoundBuffer } = require('./index.js')

const ctx = NodeAudio.makeAudioContext()

const panNode = new StereoPannerNode(ctx.sampleRate())
panNode.pan().setValue(0)

const gainNode = new GainNode(ctx.sampleRate())
gainNode.gain().setValue(0.1)

// input.connect(ctx, gainNode, 0, 0)
gainNode.connect(ctx, panNode, 0, 0)
panNode.connect(ctx, ctx.destination(), 0, 0)

// const input = NodeAudio.makeHardwareSourceNode(ctx)
const buffer = new SoundBuffer("third_party/LabSound/assets/samples/tonbi.wav", ctx.sampleRate())
buffer.playOnNode(ctx, gainNode, 0)

while(true){}