let component = ReasonReact.statelessComponent "Button";

let make ::onPress ::color ::title ::round=true _children => {
  ...component,
  render: fun () _self =>
    <TouchableOpacity
      onPress
      style=(
        ReactDOMRe.Style.make
          fontSize::"14px"
          padding::"8px"
          borderRadius::(round ? "3px" : "")
          backgroundColor::color
          color::"#fff"
          display::"inline-flex"
          ()
      )>
      (ReasonReact.stringToElement title)
    </TouchableOpacity>
};
