let component = ReasonReact.statelessComponent "SectionedListView";

module Styles = {
  let container = ReactDOMRe.Style.make flexGrow::"1" width::"100%" ();
  let sectionTitle =
    ReactDOMRe.Style.make
      padding::"10px"
      fontSize::"12px"
      textTransform::"uppercase"
      lineHeight::"1"
      color::"rgba(0, 0, 0, 0.5)"
      borderBottom::"1px solid rgba(0, 0, 0, 0.1)"
      letterSpacing::"1px"
      ();
};

let addKey index item => <div key=(string_of_int index)> item </div>;

let renderSection ::backgroundColor ::sectionBackgroundColor index (section, contents) =>
  <div
    key=(string_of_int index)
    style=(ReactDOMRe.Style.make ::backgroundColor paddingBottom::"10px" ())>
    <div style=Styles.sectionTitle> (ReasonReact.stringToElement section) </div>
    <div style=(ReactDOMRe.Style.make backgroundColor::sectionBackgroundColor ())>
      (contents |> List.mapi addKey |> Array.of_list |> ReasonReact.arrayToElement)
    </div>
  </div>;

let make
    ::sections
    ::backgroundColor="rgb(248, 248, 248)"
    ::sectionBackgroundColor="#fff"
    _children => {
  ...component,
  render: fun _self =>
    <div style=Styles.container>
      (
        sections |> List.mapi (renderSection ::backgroundColor ::sectionBackgroundColor) |> Array.of_list |> ReasonReact.arrayToElement
      )
    </div>
};
