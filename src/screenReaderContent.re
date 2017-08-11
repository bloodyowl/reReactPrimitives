let component = ReasonReact.statelessComponent "ScreenReaderContent";

let make ::text _children => {
  ...component,
  render: fun _ =>
    <div
      style=(
        ReactDOMRe.Style.make
          position::"absolute"
          clip::"rect(1px, 1px, 1px, 1px)"
          padding::"0"
          border::"0"
          height::"1px"
          width::"1px"
          overflow::"hidden"
          ()
      )>
      (ReasonReact.stringToElement text)
    </div>
};
