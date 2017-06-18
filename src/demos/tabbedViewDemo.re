let style = ReactDOMRe.Style.make padding::"10px" ();

let innerTabs = [|
  (
    ReasonReact.stringToElement "Hello",
    fun () => <div style> (ReasonReact.stringToElement "First tab") </div>
  ),
  (
    ReasonReact.stringToElement "Second tab",
    fun () =>
      <div style> (ReasonReact.stringToElement "Second tab contents") </div>
  ),
  (
    ReasonReact.stringToElement "Third tab",
    fun () =>
      <div style> (ReasonReact.stringToElement "Third tab contents") </div>
  )
|];

let tabs = [|
  (
    ReasonReact.stringToElement "Hello",
    fun () => <TabbedView tabs=innerTabs />
  ),
  (
    ReasonReact.stringToElement "Second tab",
    fun () =>
      <div style> (ReasonReact.stringToElement "Second tab contents") </div>
  ),
  (
    ReasonReact.stringToElement "Third tab",
    fun () =>
      <div style> (ReasonReact.stringToElement "Third tab contents") </div>
  )
|];

ReactDOMRe.renderToElementWithId <TabbedView tabs mode=Horizontal /> "root";
