let component = ReasonReact.statelessComponent "Dialog";

module Styles = {
  let root =
    ReactDOMRe.Style.make
      display::"flex"
      flexDirection::"column"
      alignItems::"center"
      justifyContent::"flex-start"
      padding::"40px 10px"
      width::"100vw"
      height::"100vh"
      ();
  let container =
    ReactDOMRe.Style.make
      backgroundColor::"#fff"
      borderRadius::"4px"
      boxShadow::"0 2px 4px rgba(0, 0, 0, 0.16)"
      position::"relative"
      ();
  let header =
    ReactDOMRe.Style.make
      display::"flex"
      flexDirection::"row"
      alignItems::"center"
      borderBottom::"1px solid rgba(0, 0, 0, 0.1)"
      ();
  let headerText =
    ReactDOMRe.Style.make
      flexGrow::"1"
      display::"flex"
      flexDirection::"column"
      alignItems::"flex-start"
      padding::"10px"
      ();
  let headerTitle =
    ReactDOMRe.Style.make fontSize::"16px" fontWeight::"700" color::"rgba(0, 0, 0, 0.4)" ();
  let headerDescription = ReactDOMRe.Style.make fontSize::"12px" color::"rgba(0, 0, 0, 0.4)" ();
  let close = ReactDOMRe.Style.make padding::"10px" ();
  let closeIcon = ReactDOMRe.Style.make opacity::"0.4" ();
};

let make
    ::title
    ::description=?
    ::onPressClose
    ::minWidth=0
    ::underlayColor="rgba(0, 0, 0, 0.3)"
    children => {
  ...component,
  render: fun _self =>
    <div style=Styles.root>
      <div
        onClick=(fun _ => onPressClose ())
        style=(
          ReactDOMRe.Style.make
            position::"fixed"
            top::"0"
            left::"0"
            right::"0"
            bottom::"0"
            backgroundColor::underlayColor
            ()
        )
      />
      <div
        style=(
          ReactDOMRe.Style.combine
            Styles.container (ReactDOMRe.Style.make minWidth::(string_of_int minWidth ^ "px") ())
        )
        role="dialog">
        <div style=Styles.header>
          <div style=Styles.headerText>
            <Text style=Styles.headerTitle> (ReasonReact.stringToElement title) </Text>
            (
              switch description {
              | Some description =>
                <Text style=Styles.headerDescription>
                  (ReasonReact.stringToElement description)
                </Text>
              | None => ReasonReact.nullElement
              }
            )
          </div>
          <TouchableOpacity onPress=onPressClose style=Styles.close>
            <span style=Styles.closeIcon> (ReasonReact.stringToElement {js|✖️|js}) </span>
          </TouchableOpacity>
        </div>
        <div> children.(0) </div>
      </div>
    </div>
};
