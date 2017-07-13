let component = ReasonReact.statelessComponent "HorizontalSeparator";

let make ::color="rgba(0, 0, 0, 0.1)" ::verticalSpace=5 _ => {
  ...component,
  render: fun _self =>
    <div
      style=(
        ReactDOMRe.Style.make
          height::"1px"
          backgroundColor::color
          marginTop::(string_of_int verticalSpace ^ "px")
          marginBottom::(string_of_int verticalSpace ^ "px")
          width::"100%"
          ()
      )
    />
};
