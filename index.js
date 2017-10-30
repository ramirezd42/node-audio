const nbind = require('nbind')
const binding = nbind.init(__dirname);
const lib = binding.lib;
lib.NodeAudioConfig.setModulePath(__dirname);
module.exports = lib
