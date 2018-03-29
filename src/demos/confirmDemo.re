module MyLayerManager = LayerManager.Make(LayerManager.DefaultImpl);

let openConfirm = (_) => {
  let layer = MyLayerManager.make(FullViewport);
  Js.Promise.then_(
    layer => {
      MyLayerManager.render(
        layer,
        <Confirm
          message="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum id ligula porta felis euismod semper."
          confirmWording="Yay, confirmed!"
          cancelWording="Nay"
          onConfirm=((_) => Js.log("onConfirm"))
          onCancel=((_) => Js.log("onCancel"))
        />,
      );
      Js.Promise.resolve();
    },
    layer,
  );
};

ReactDOMRe.renderToElementWithId(
  <div>
    <Button title="Open confirm" color="#fb5" onPress=openConfirm />
  </div>,
  "root",
);
