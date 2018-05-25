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
          onConfirm=(
            (_) => {
              Js.log("onConfirm");
              MyLayerManager.remove(layer);
            }
          )
          onCancel=(
            (_) => {
              Js.log("onCancel");
              MyLayerManager.remove(layer);
            }
          )
        />,
      );
      Js.Promise.resolve();
    },
    layer,
  );
};

let openConfirmChild = (_) => {
  let layer = MyLayerManager.make(FullViewport);
  Js.Promise.then_(
    layer => {
      MyLayerManager.render(
        layer,
        <Confirm
          onConfirm=(
            (_) => {
              Js.log("onConfirm");
              MyLayerManager.remove(layer);
            }
          )
          onCancel=(
            (_) => {
              Js.log("onCancel");
              MyLayerManager.remove(layer);
            }
          )
          confirmWording="Yay, confirmed!"
          cancelWording="Nay">
          <div>
            (ReasonReact.string("First child"))
            <strong> (ReasonReact.string(" (of three) ")) </strong>
            (ReasonReact.string("with a list"))
            <ul>
              <li> (ReasonReact.string("id ")) </li>
              <li> (ReasonReact.string("ligula")) </li>
              <li> (ReasonReact.string("porta felis euismod semper")) </li>
            </ul>
          </div>
          <div> (ReasonReact.string("Second child")) </div>
          <div> (ReasonReact.string("Third child")) </div>
        </Confirm>,
      );
      Js.Promise.resolve();
    },
    layer,
  );
};

let openConfirmAll = (_) => {
  let layer = MyLayerManager.make(FullViewport);
  Js.Promise.then_(
    layer => {
      MyLayerManager.render(
        layer,
        <Confirm
          onConfirm=(
            (_) => {
              Js.log("onConfirm");
              MyLayerManager.remove(layer);
            }
          )
          onCancel=(
            (_) => {
              Js.log("onCancel");
              MyLayerManager.remove(layer);
            }
          )
          confirmWording="Yay, confirmed!"
          cancelWording="Nay"
          message="Text from ~message">
          <div>
            (ReasonReact.string("Text from "))
            <strong> (ReasonReact.string("children")) </strong>
          </div>
        </Confirm>,
      );
      Js.Promise.resolve();
    },
    layer,
  );
};

ReactDOMRe.renderToElementWithId(
  <div>
    <Button title="Open confirm" color="#fb5" onPress=openConfirm />
    <br />
    <Button
      title="Open confirm (child)"
      color="#4A90E2"
      onPress=openConfirmChild
    />
    <br />
    <Button
      title="Open confirm (message + child)"
      color="#7ED321"
      onPress=openConfirmAll
    />
  </div>,
  "root",
);
