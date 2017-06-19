const path = require('path');

module.exports = {
  entry: {
    activityIndicatorDemo: './lib/js/src/demos/activityIndicatorDemo',
    touchableOpacityDemo: './lib/js/src/demos/touchableOpacityDemo',
    touchableHighlightDemo: './lib/js/src/demos/touchableHighlightDemo',
    buttonDemo: './lib/js/src/demos/buttonDemo',
    imageDemo: './lib/js/src/demos/imageDemo',
    spriteDemo: './lib/js/src/demos/spriteDemo',
    textInputDemo: './lib/js/src/demos/textInputDemo',
    switchDemo: './lib/js/src/demos/switchDemo',
    sectionedListViewDemo: './lib/js/src/demos/sectionedListViewDemo',
    tabbedViewDemo: './lib/js/src/demos/tabbedViewDemo',
    timePickerDemo: './lib/js/src/demos/timePickerDemo',
    dialogDemo: './lib/js/src/demos/dialogDemo',
    tooltipDemo: './lib/js/src/demos/tooltipDemo',
    fixedCollectionViewDemo: './lib/js/src/demos/fixedCollectionViewDemo',
  },
  output: {
    path: path.join(__dirname, 'bundledOutputs'),
    filename: '[name].js',
  },
};
