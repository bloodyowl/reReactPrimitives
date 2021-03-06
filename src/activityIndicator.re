[@bs.get]
external getDevicePixelRatio :
  DomRe.Window.t_window => Js.Null_undefined.t(float) =
  "devicePixelRatio";

let devicePixelRatio =
  switch (Js.Null_undefined.toOption(getDevicePixelRatio(DomRe.window))) {
  | Some(value) => value
  | None => 1.0
  };

type state = {
  context: ref(option(Webapi.Canvas.Canvas2d.t)),
  cancelNextFrame: ref(bool),
};

type action =
  | Draw;

let component = ReasonReact.reducerComponent("ActivityIndicator");

let tupleToColor = ((r, g, b), alpha) =>
  "rgba("
  ++ string_of_int(r)
  ++ ","
  ++ string_of_int(g)
  ++ ","
  ++ string_of_int(b)
  ++ ","
  ++ string_of_float(alpha)
  ++ "0)";

let setCanvasRef = (canvasRef, {ReasonReact.state}) =>
  state.context :=
    (
      switch (Js.Nullable.toOption(canvasRef)) {
      | Some(canvas) =>
        Some(Webapi.Canvas.CanvasElement.getContext2d(canvas))
      | None => None
      }
    );

let draw = (~size, ~color, {ReasonReact.state}) =>
  switch (state.context) {
  | {contents: Some(context)} =>
    let actualSize = size *. devicePixelRatio;
    Webapi.Canvas.Canvas2d.clearRect(
      ~x=0.0,
      ~y=0.0,
      ~w=actualSize,
      ~h=actualSize,
      context,
    );
    Webapi.Canvas.Canvas2d.translate(
      ~x=actualSize /. 2.0,
      ~y=actualSize /. 2.0,
      context,
    );
    Webapi.Canvas.Canvas2d.rotate(0.172665, context);
    Webapi.Canvas.Canvas2d.translate(
      ~x=0.0 -. actualSize /. 2.0,
      ~y=0.0 -. actualSize /. 2.0,
      context,
    );
    let centeredArc =
      Webapi.Canvas.Canvas2d.arc(~x=actualSize /. 2.0, ~y=actualSize /. 2.0);
    Webapi.Canvas.Canvas2d.beginPath(context);
    centeredArc(
      ~r=actualSize *. 0.5,
      ~startAngle=Js.Math._PI,
      ~endAngle=0.0,
      ~anticw=false,
      context,
    );
    centeredArc(
      ~r=actualSize *. 0.3,
      ~startAngle=0.0,
      ~endAngle=Js.Math._PI,
      ~anticw=true,
      context,
    );
    Webapi.Canvas.Canvas2d.setFillStyle(
      context,
      String,
      tupleToColor(color, 1.0),
    );
    Webapi.Canvas.Canvas2d.fill(context);
    Webapi.Canvas.Canvas2d.closePath(context);
    Webapi.Canvas.Canvas2d.beginPath(context);
    centeredArc(
      ~r=actualSize *. 0.5,
      ~startAngle=0.0,
      ~endAngle=Js.Math._PI,
      ~anticw=false,
      context,
    );
    centeredArc(
      ~r=actualSize *. 0.3,
      ~startAngle=Js.Math._PI,
      ~endAngle=0.0,
      ~anticw=true,
      context,
    );
    let gradient =
      Webapi.Canvas.Canvas2d.createLinearGradient(
        ~x0=0.0,
        ~y0=actualSize *. 0.5,
        ~x1=actualSize *. 0.75,
        ~y1=actualSize *. 0.5,
        context,
      );
    Webapi.Canvas.Canvas2d.addColorStop(
      0.5,
      tupleToColor(color, 1.0),
      gradient,
    );
    Webapi.Canvas.Canvas2d.addColorStop(
      1.0,
      tupleToColor(color, 0.0),
      gradient,
    );
    Webapi.Canvas.Canvas2d.setFillStyle(context, Gradient, gradient);
    Webapi.Canvas.Canvas2d.fill(context);
    ();
  | _ => ()
  };

let make = (~size, ~color, _children) => {
  let tick = ({ReasonReact.send, ReasonReact.state} as self) =>
    Webapi.requestAnimationFrame((_) =>
      switch (state.cancelNextFrame) {
      | {contents: false} =>
        draw(~size, ~color, self);
        send(Draw);
      | _ => ()
      }
    );
  {
    ...component,
    initialState: () => {context: ref(None), cancelNextFrame: ref(false)},
    didMount: ({send}) => send(Draw),
    reducer: (action, state) =>
      switch (action) {
      | Draw =>
        switch (state.cancelNextFrame) {
        | {contents: false} => ReasonReact.SideEffects(tick)
        | _ => ReasonReact.NoUpdate
        }
      },
    willUnmount: ({state}) => state.cancelNextFrame := true,
    render: self => {
      let sizeAttr = string_of_int(int_of_float(size));
      let actualSize = string_of_int(int_of_float(size *. devicePixelRatio));
      <canvas
        ref=(self.handle(setCanvasRef))
        width=actualSize
        height=actualSize
        style=(
          ReactDOMRe.Style.make(
            ~width=sizeAttr ++ "px",
            ~height=sizeAttr ++ "px",
            (),
          )
        )
      />;
    },
  };
};