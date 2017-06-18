type state = bool;

let component = ReasonReact.statefulComponent "Picker";

let make
    ::options
    ::renderOption
    ::multiple=false
    ::value
    ::onValueChange
    _children => {
  ...component,
  initialState: fun () => false,
  render: fun state self =>
    <div> (state ? <div /> : ReasonReact.nullElement) </div>
};
