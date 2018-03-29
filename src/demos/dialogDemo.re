module MyLayerManager = LayerManager.Make(LayerManager.DefaultImpl);

let openDialog = (_) => {
  let layer = MyLayerManager.make(FullViewport);
  Js.Promise.then_(
    layer => {
      MyLayerManager.render(
        layer,
        <Dialog
          title="Hello"
          description="This is a dialog"
          onPressClose=((_) => MyLayerManager.remove(layer))
          minWidth=100
          maxWidth=200>
          <div style=(ReactDOMRe.Style.make(~padding="10px", ()))>
            (ReasonReact.stringToElement("This is a dialog"))
          </div>
        </Dialog>,
      );
      Js.Promise.resolve();
    },
    layer,
  );
};

let openDialog2 = (_) => {
  let layer = MyLayerManager.make(FullViewport);
  Js.Promise.then_(
    layer => {
      MyLayerManager.render(
        layer,
        <Dialog
          title="NullavitaeelitliberoapharetraaugueSedposuereconsecteturestatlobortisCrasjustoodiodapibusacfacilisisinegestasegetquamIntegerposuereerataantevenenatisdapibusposuerevelitaliquetMorbileorisusporta ac consectetur ac, vestibulum at eros. Etiam porta sem malesuada magna mollis euismod. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Aenean lacinia bibendum nulla sed consectetur. Nulla vitae elit libero, a pharetra augue."
          description="FuscedapibustellusaccursuscommodotortormauriscondimentumnibhutfermentummassajustositametrisusMaecenasfaucibusmollisinterdumNullavitaeelitliberoapharetraaugueDonecullamcorpernullanonmetusauctorfringillaDuismollisestnoncommodo luctus nisi erat porttitor ligula, eget lacinia odio sem nec elit. Etiam porta sem malesuada magna mollis euismod. Donec ullamcorper nulla non metus auctor fringilla. Maecenas faucibus mollis interdum. Aenean eu leo quam. Pellentesque ornare sem lacinia quam venenatis vestibulum. Maecenas sed diam eget risus varius blandit sit amet non magna."
          onPressClose=((_) => MyLayerManager.remove(layer))
          minWidth=100>
          <div style=(ReactDOMRe.Style.make(~padding="10px", ()))>
            (ReasonReact.stringToElement("This is a dialog"))
          </div>
        </Dialog>,
      );
      Js.Promise.resolve();
    },
    layer,
  );
};

let openDialog3 = (_) => {
  let layer = MyLayerManager.make(FullViewport);
  Js.Promise.then_(
    layer => {
      MyLayerManager.render(
        layer,
        <Dialog
          title="Hello"
          description="This is a dialog"
          onPressClose=((_) => MyLayerManager.remove(layer))
          minWidth=100
          maxWidth=200>
          <ScrollView>
            (
              Array.make(
                100,
                <div style=(ReactDOMRe.Style.make(~padding="10px", ()))>
                  (ReasonReact.stringToElement("This is a dialog"))
                </div>,
              )
              |> Array.mapi((index, item) =>
                   ReasonReact.cloneElement(
                     item,
                     ~props={"key": string_of_int(index)},
                     [||],
                   )
                 )
              |> ReasonReact.arrayToElement
            )
          </ScrollView>
        </Dialog>,
      );
      Js.Promise.resolve();
    },
    layer,
  );
};

ReactDOMRe.renderToElementWithId(
  <div>
    <Button
      title="Open dialog (max-width set)"
      color="#fb5"
      onPress=openDialog
    />
    <br />
    <br />
    <Button
      title="Open dialog (too much text)"
      color="#fb5"
      onPress=openDialog2
    />
    <br />
    <br />
    <Button
      title="Open dialog (scrollView)"
      color="#fb5"
      onPress=openDialog3
    />
  </div>,
  "root",
);
