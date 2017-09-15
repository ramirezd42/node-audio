const { NodeAudio } = require('./index.js')

const ctx = NodeAudio.makeAudioContext()
const source = NodeAudio.makeHardwareSourceNode(ctx)
source.connect(ctx, ctx.destination(), 0, 0);
console.log(source)
while(true){}