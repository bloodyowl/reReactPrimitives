type state = option LayerManager.layer;

let component = ReasonReact.statefulComponent "Picker";

module PickerLayerManager = LayerManager.Make LayerManager.DefaultImpl;

let make ::options ::renderPicker ::renderOption ::value ::onValueChange ::padding="10px" _children => {
  let hideOptions _ state _self =>
    switch state {
    | Some layer =>
      PickerLayerManager.remove layer;
      ReasonReact.SilentUpdate None
    | None => ReasonReact.NoUpdate
    };
  let renderOptionWithEvent _state self index item =>
    <TouchableHighlight
      key=(string_of_int index)
      onPress=(
        fun _ => {
          onValueChange (Some item);
          self.ReasonReact.update hideOptions ()
        }
      )
      style=(ReactDOMRe.Style.make cursor::"pointer" ())
      underlayColor="rgba(0, 0, 0, 0.05)">
      (renderOption item value)
    </TouchableHighlight>;
  let whenLayerReady layer state self => {
    PickerLayerManager.render
      layer
      <div>
        <div
          onClick=(fun _ => self.ReasonReact.update hideOptions ())
          style=(
            ReactDOMRe.Style.make
              position::"fixed"
              top::"0"
              left::"0"
              right::"0"
              bottom::"0"
              ()
          )
        />
        <div
          style=(
            ReactDOMRe.Style.make
              position::"relative"
              backgroundColor::"#fff"
              borderBottomLeftRadius::"3px"
              borderBottomRightRadius::"3px"
              boxShadow::"0 2px 4px rgba(0, 0, 0, 0.16"
              ()
          )>
          (
            options |> List.mapi (renderOptionWithEvent state self) |> Array.of_list |> ReasonReact.arrayToElement
          )
        </div>
      </div>;
    ReasonReact.SilentUpdate (Some layer)
  };
  let showOptions event state self =>
    switch state {
    | Some _layer => hideOptions () state self
    | None =>
      let layer =
        PickerLayerManager.make (Contextualized (ReactEventRe.Mouse.target event) Bottom);
      ignore (
        Js.Promise.then_
          (
            fun layer => {
              self.ReasonReact.update whenLayerReady layer;
              Js.Promise.resolve ()
            }
          )
          layer
      );
      ReasonReact.NoUpdate
    };
  {
    ...component,
    initialState: fun () => None,
    render: fun _state self =>
      <div
        style=(ReactDOMRe.Style.make ::padding cursor::"pointer" ())
        onClick=(self.update showOptions)>
        (renderPicker value)
      </div>
  }
};
