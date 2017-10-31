let component = ReasonReact.statelessComponent("Button");

let make = (~onPress, ~color, ~title, ~disabled=false, ~round=true, _children) => {
  ...component,
  render: (_self) =>
    <TouchableOpacity
      onPress
      style=(
        ReactDOMRe.Style.make(
          ~fontSize="14px",
          ~padding="8px",
          ~borderRadius=round ? "3px" : "",
          ~backgroundColor=color,
          ~color="#fff",
          ~display="inline-flex",
          ()
        )
      )
      focusedFromKeyboardStyle=(
        ReactDOMRe.Style.make(
          ~outline="none",
          ~backgroundImage="linear-gradient(to bottom, rgba(0, 0, 0, 0.1), rgba(0, 0, 0, 0.1))",
          ()
        )
      )
      disabledStyle=(ReactDOMRe.Style.make(~opacity="0.4", ~outline="none", ~cursor="default", ()))
      disabled>
      (ReasonReact.stringToElement(title))
    </TouchableOpacity>
};
