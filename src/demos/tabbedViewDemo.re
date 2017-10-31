let style = ReactDOMRe.Style.make(~padding="10px", ());

let innerTabs = [|
  (
    ReasonReact.stringToElement("Hello"),
    () => <div style> (ReasonReact.stringToElement("First tab")) </div>
  ),
  (
    ReasonReact.stringToElement("Second tab"),
    () => <div style> (ReasonReact.stringToElement("Second tab contents")) </div>
  ),
  (
    ReasonReact.stringToElement("Third tab"),
    () => <div style> (ReasonReact.stringToElement("Third tab contents")) </div>
  )
|];

let tabs = [|
  (ReasonReact.stringToElement("Hello"), () => <TabbedView tabs=innerTabs />),
  (
    ReasonReact.stringToElement("Second tab"),
    () => <div style> (ReasonReact.stringToElement("Second tab contents")) </div>
  ),
  (
    ReasonReact.stringToElement("Third tab"),
    () => <div style> (ReasonReact.stringToElement("Third tab contents")) </div>
  )
|];

ReactDOMRe.renderToElementWithId(<TabbedView tabs mode=Horizontal />, "root");
