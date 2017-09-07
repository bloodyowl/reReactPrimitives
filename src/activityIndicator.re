external devicePixelRatio : float = "devicePixelRatio" [@@bs.val];

type state = {
  context: ref (option ReasonJs.Canvas2d.t),
  cancelNextFrame: ref bool
};

type action =
  | Draw;

let component = ReasonReact.reducerComponent "ActivityIndicator";

let tupleToColor (r, g, b) alpha =>
  "rgba("
  ^ string_of_int r
  ^ ","
  ^ string_of_int g
  ^ ","
  ^ string_of_int b
  ^ ","
  ^ string_of_float alpha
  ^ "0)";

let setCanvasRef canvasRef {ReasonReact.state: state} =>
  state.context :=
    (
      switch (Js.Null.to_opt canvasRef) {
      | Some canvas => Some (ReasonJs.CanvasElement.getContext2d canvas)
      | None => None
      }
    );

let draw ::size ::color {ReasonReact.state: state} =>
  switch state.context {
  | {contents: Some context} =>
    let actualSize = size *. devicePixelRatio;
    ReasonJs.Canvas2d.clearRect x::0.0 y::0.0 w::actualSize h::actualSize context;
    ReasonJs.Canvas2d.translate x::(actualSize /. 2.0) y::(actualSize /. 2.0) context;
    ReasonJs.Canvas2d.rotate 0.172665 context;
    ReasonJs.Canvas2d.translate x::(-. (actualSize /. 2.0)) y::(-. (actualSize /. 2.0)) context;
    let centeredArc = ReasonJs.Canvas2d.arc x::(actualSize /. 2.0) y::(actualSize /. 2.0);
    ReasonJs.Canvas2d.beginPath context;
    centeredArc
      r::(actualSize *. 0.5) startAngle::Js.Math._PI endAngle::0.0 anticw::Js.false_ context;
    centeredArc
      r::(actualSize *. 0.3) startAngle::0.0 endAngle::Js.Math._PI anticw::Js.true_ context;
    ReasonJs.Canvas2d.setFillStyle context String (tupleToColor color 1.0);
    ReasonJs.Canvas2d.fill context;
    ReasonJs.Canvas2d.closePath context;
    ReasonJs.Canvas2d.beginPath context;
    centeredArc
      r::(actualSize *. 0.5) startAngle::0.0 endAngle::Js.Math._PI anticw::Js.false_ context;
    centeredArc
      r::(actualSize *. 0.3) startAngle::Js.Math._PI endAngle::0.0 anticw::Js.true_ context;
    let gradient =
      ReasonJs.Canvas2d.createLinearGradient
        x0::0.0 y0::(actualSize *. 0.5) x1::(actualSize *. 0.75) y1::(actualSize *. 0.5) context;
    ReasonJs.Canvas2d.addColorStop 0.5 (tupleToColor color 1.0) gradient;
    ReasonJs.Canvas2d.addColorStop 1.0 (tupleToColor color 0.0) gradient;
    ReasonJs.Canvas2d.setFillStyle context Gradient gradient;
    ReasonJs.Canvas2d.fill context;
    ()
  | _ => ()
  };

let make ::size ::color _children => {
  let tick ({ReasonReact.reduce: reduce} as self) =>
    Bs_webapi.requestAnimationFrame (
      fun _ => {
        draw ::size ::color self;
        reduce (fun () => Draw) ()
      }
    );
  {
    ...component,
    initialState: fun () => {context: ref None, cancelNextFrame: ref false},
    didMount: fun {state, reduce} => {
      reduce (fun () => Draw) ();
      ReasonReact.NoUpdate
    },
    reducer: fun action state =>
      switch action {
      | Draw =>
        switch state.cancelNextFrame {
        | {contents: false} => ReasonReact.SideEffects tick
        | _ => ReasonReact.NoUpdate
        }
      },
    willUnmount: fun {state} => state.cancelNextFrame := true,
    render: fun self => {
      let sizeAttr = string_of_int (int_of_float size);
      let actualSize = string_of_int (int_of_float (size *. devicePixelRatio));
      <canvas
        ref=(self.handle setCanvasRef)
        width=actualSize
        height=actualSize
        style=(ReactDOMRe.Style.make width::(sizeAttr ^ "px") height::(sizeAttr ^ "px") ())
      />
    }
  }
};
