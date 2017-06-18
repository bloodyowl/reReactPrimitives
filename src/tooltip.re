type state =
  | Visible
  | Hidden;

let component = ReasonReact.statefulComponent "Tooltip";

let make ::message children => {
  ...component,
  initialState: fun () => Hidden,
  render: fun state _self =>
    <div>
      (ReasonReact.arrayToElement children)
      (
        switch state {
        | Visible => <div />
        | Hidden => ReasonReact.nullElement
        }
      )
    </div>
};
