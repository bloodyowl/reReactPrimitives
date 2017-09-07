let component = ReasonReact.statelessComponent "ListView";

let defaultRenderSeparator () =>
  <div style=(ReactDOMRe.Style.make borderBottom::"1px solid rgba(0, 0, 0, 0.1)" ()) />;

let make ::style=? ::items ::renderItem ::renderSeparator=defaultRenderSeparator _children => {
  ...component,
  render: fun _self =>
    <div style=?style>
      (
        items
        |> List.fold_left
             (fun acc item => List.append acc [renderSeparator (), renderItem item]) []
        |> List.tl
        |> List.mapi (fun index item => <div key=(string_of_int index)> item </div>)
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>
};
