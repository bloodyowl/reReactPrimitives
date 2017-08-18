const path = require("path")

module.exports = {
  entry : {
    activityIndicatorDemo : "./lib/js/src/demos/activityIndicatorDemo",
    touchableOpacityDemo : "./lib/js/src/demos/touchableOpacityDemo",
    touchableHighlightDemo : "./lib/js/src/demos/touchableHighlightDemo",
    buttonDemo : "./lib/js/src/demos/buttonDemo",
    pickerDemo : "./lib/js/src/demos/pickerDemo",
    imageDemo : "./lib/js/src/demos/imageDemo",
    spriteDemo : "./lib/js/src/demos/spriteDemo",
    textInputDemo : "./lib/js/src/demos/textInputDemo",
    switchDemo : "./lib/js/src/demos/switchDemo",
    sectionedListViewDemo : "./lib/js/src/demos/sectionedListViewDemo",
    tabbedViewDemo : "./lib/js/src/demos/tabbedViewDemo",
    confirmDemo : "./lib/js/src/demos/confirmDemo",
    dialogDemo : "./lib/js/src/demos/dialogDemo",
    listViewDemo : "./lib/js/src/demos/listViewDemo",
    tooltipDemo : "./lib/js/src/demos/tooltipDemo",
    fixedCollectionViewDemo : "./lib/js/src/demos/fixedCollectionViewDemo",
    segmentedControlDemo : "./lib/js/src/demos/segmentedControlDemo",
  },
  output : {
    path : path.join(__dirname, "demos/bundledOutputs"),
    filename : "[name].js",
  },
}
