let itemStyle =
  ReactDOMRe.Style.make(
    ~padding="10px",
    ~borderBottom="1px solid rgba(0, 0, 0, 0.1)",
    (),
  );

let sections = [
  (
    "Schedule",
    [
      <div style=itemStyle> (ReasonReact.string("Foo")) </div>,
      <div style=itemStyle> (ReasonReact.string("Bar")) </div>,
    ],
  ),
  (
    "Display",
    [
      <div style=itemStyle> (ReasonReact.string("Baz")) </div>,
      <div style=itemStyle> (ReasonReact.string("Quux")) </div>,
    ],
  ),
];

ReactDOMRe.renderToElementWithId(
  <div style=(ReactDOMRe.Style.make(~width="100%", ()))>
    <SectionedListView sections />
    <SectionedListView
      sections
      backgroundColor="#eee"
      sectionBackgroundColor="#fff"
    />
  </div>,
  "root",
);
