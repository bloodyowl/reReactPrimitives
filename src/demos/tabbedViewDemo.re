let style = ReactDOMRe.Style.make(~padding="10px", ());

let innerTabs = [|
  (
    ReasonReact.string("Hello"),
    () => <div style> (ReasonReact.string("First tab")) </div>,
  ),
  (
    ReasonReact.string("Second tab"),
    () => <div style> (ReasonReact.string("Second tab contents")) </div>,
  ),
  (
    ReasonReact.string("Third tab"),
    () => <div style> (ReasonReact.string("Third tab contents")) </div>,
  ),
|];

let tabs = [|
  (ReasonReact.string("Hello"), () => <TabbedView tabs=innerTabs />),
  (
    ReasonReact.string("Second tab"),
    () => <div style> (ReasonReact.string("Second tab contents")) </div>,
  ),
  (
    ReasonReact.string("Third tab"),
    () => <div style> (ReasonReact.string("Third tab contents")) </div>,
  ),
|];

ReactDOMRe.renderToElementWithId(<TabbedView tabs mode=Horizontal />, "root");
