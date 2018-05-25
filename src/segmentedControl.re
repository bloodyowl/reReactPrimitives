let component = ReasonReact.statelessComponent("SegmentedControl");

type segment('a) = (string, 'a);

let make = (~segments, ~activeSegment, ~color, ~onSegmentPress, _children) => {
  ...component,
  render: _self =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~overflow="hidden",
          ~borderRadius="3px",
          ~border="1px solid " ++ color,
          ~display="flex",
          ~flexDirection="row",
          (),
        )
      )>
      (
        segments
        |> List.mapi((index, (title, value)) =>
             <TouchableOpacity
               key=(string_of_int(index))
               style=(
                 ReactDOMRe.Style.combine(
                   ReactDOMRe.Style.make(
                     ~flexGrow="1",
                     ~textAlign="center",
                     ~padding="5px",
                     ~fontSize="14px",
                     ~boxShadow="1px 0 " ++ color,
                     (),
                   ),
                   value == activeSegment ?
                     ReactDOMRe.Style.make(
                       ~backgroundColor=color,
                       ~color="#fff",
                       (),
                     ) :
                     ReactDOMRe.Style.make(~color, ()),
                 )
               )
               onPress=((_) => onSegmentPress(value))>
               (ReasonReact.string(title))
             </TouchableOpacity>
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>,
};
