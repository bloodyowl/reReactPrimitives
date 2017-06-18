let itemStyle =
  ReactDOMRe.Style.make
    padding::"10px" borderBottom::"1px solid rgba(0, 0, 0, 0.1)" ();

let sections = [
  (
    "Schedule",
    [
      <div style=itemStyle> (ReasonReact.stringToElement "Foo") </div>,
      <div style=itemStyle> (ReasonReact.stringToElement "Bar") </div>
    ]
  ),
  (
    "Display",
    [
      <div style=itemStyle> (ReasonReact.stringToElement "Baz") </div>,
      <div style=itemStyle> (ReasonReact.stringToElement "Quux") </div>
    ]
  )
];

ReactDOMRe.renderToElementWithId <SectionedListView sections /> "root";
