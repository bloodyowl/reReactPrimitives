type state = option (int, int);

let component = ReasonReact.statefulComponent "TimePicker";

module Styles = {
  let input =
    ReactDOMRe.Style.make
      border::"none"
      padding::"10px"
      backgroundColor::"rgba(0, 0, 0, 0.05)"
      width::"30px"
      borderRadius::"3px"
      ();
};

let make ::value ::timezone="GMT" _children => {
  ...component,
  initialState: fun () => None,
  render: fun state _self => {
    let (hours, minutes) = value;
    <div>
      <TextInput
        style=Styles.input
        value=(
          string_of_int (
            switch state {
            | Some (stateHours, _stateMinutes) => stateHours
            | None => hours
            }
          )
        )
        onTextChange=(fun _ => ())
      />
      (ReasonReact.stringToElement ":")
      <TextInput
        style=Styles.input
        value=(
          string_of_int (
            switch state {
            | Some (_stateHours, stateMinutes) => stateMinutes
            | None => minutes
            }
          )
        )
        onTextChange=(fun _ => ())
      />
      (ReasonReact.stringToElement timezone)
    </div>
  }
};
