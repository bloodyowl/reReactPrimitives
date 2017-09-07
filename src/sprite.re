module type SpriteSheetType = {let width: int; let height: int; let url: string;};

module Make (SpriteSheet: SpriteSheetType) => {
  let basename = {
    let index = String.rindex SpriteSheet.url '/' + 1;
    String.sub SpriteSheet.url index (String.length SpriteSheet.url - index)
  };
  type state = {isReady: bool};
  let component = ReasonReact.reducerComponent ("Sprite[" ^ basename ^ "]");
  let make ::width ::height ::x ::y _children => {
    ...component,
    initialState: fun _ => {isReady: false},
    reducer: fun () _state => ReasonReact.NoUpdate,
    didMount: fun _self => ReasonReact.Update {isReady: true},
    render: fun {state} =>
      <div
        style=(
          ReactDOMRe.Style.make
            width::(string_of_int width ^ "px")
            height::(string_of_int height ^ "px")
            backgroundSize::(
              string_of_int SpriteSheet.width ^ "px " ^ string_of_int SpriteSheet.height ^ "px"
            )
            backgroundPosition::("-" ^ string_of_int x ^ "px " ^ "-" ^ string_of_int y ^ "px")
            backgroundImage::(state.isReady ? "url(" ^ SpriteSheet.url ^ ")" : "")
            ()
        )
      />
  };
};
