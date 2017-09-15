const nbind = require('nbind')

nbind.init();

nbind.init(__dirname, (err, binding) => {
  if(err) throw(err);

  const lib = binding.lib;
  const ctx = lib.NodeAudio.makeAudioContext()
  const source = lib.NodeAudio.makeHardwareSourceNode(ctx)
  source.connect(ctx, ctx.destination(), 0, 0);
  console.log(source)
});

while(true){}