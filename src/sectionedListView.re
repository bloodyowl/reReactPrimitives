let component = ReasonReact.statelessComponent "SectionedListView";

module Styles = {
  let container =
    ReactDOMRe.Style.make flexGrow::"1" width::"100%" backgroundColor::"rgba(0, 0, 0, 0.05)" ();
  let sectionTitle = ReactDOMRe.Style.make padding::"10px" fontSize::"20px" fontWeight::"900" ();
  let sectionContents = ReactDOMRe.Style.make backgroundColor::"#fff" ();
};

let addKey index item => <div key=(string_of_int index)> item </div>;

let renderSection index (section, contents) =>
  <div key=(string_of_int index)>
    <div style=Styles.sectionTitle> (ReasonReact.stringToElement section) </div>
    <div style=Styles.sectionContents>
      (contents |> List.mapi addKey |> Array.of_list |> ReasonReact.arrayToElement)
    </div>
  </div>;

let make ::sections _children => {
  ...component,
  render: fun () _self =>
    <div style=Styles.container>
      (sections |> List.mapi renderSection |> Array.of_list |> ReasonReact.arrayToElement)
    </div>
};
