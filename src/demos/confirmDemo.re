module MyLayerManager = LayerManager.Make LayerManager.DefaultImpl;

let openConfirm _ => {
  let layer = MyLayerManager.make FullViewport;
  Js.Promise.then_
    (
      fun layer => {
        MyLayerManager.render
          layer
          <Confirm
            message="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum id ligula porta felis euismod semper."
            confirmWording="Yay, confirmed!"
            cancelWording="Nay"
            onConfirm=(fun _ => Js.log "onConfirm")
            onCancel=(fun _ => Js.log "onCancel")
          />;
        Js.Promise.resolve ()
      }
    )
    layer
};

ReactDOMRe.renderToElementWithId
  <div> <Button title="Open confirm" color="#fb5" onPress=openConfirm /> </div> "root";
