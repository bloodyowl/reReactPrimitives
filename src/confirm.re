let component = ReasonReact.statelessComponent("Confirm");

module Styles = {
  let root =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="column",
      ~justifyContent="center",
      ~width="100vw",
      ~height="100vh",
      ~alignItems="center",
      ~boxSizing="border-box",
      (),
    );
  let layer =
    ReactDOMRe.Style.make(
      ~position="fixed",
      ~top="0",
      ~left="0",
      ~right="0",
      ~bottom="0",
      ~backgroundColor="rgba(0, 0, 0, 0.3)",
      ~transition="background-color .5s ease-in-out",
      (),
    );
  let container =
    ReactDOMRe.Style.make(
      ~backgroundColor="#fff",
      ~borderRadius="4px",
      ~boxShadow="0 2px 4px rgba(0, 0, 0, 0.16)",
      ~position="relative",
      ~margin="10px",
      ~overflow="hidden",
      ~zIndex="0",
      (),
    );
  let icon =
    ReactDOMRe.Style.make(
      ~padding="10px",
      ~display="flex",
      ~flexDirection="row",
      ~alignItems="center",
      ~justifyContent="center",
      (),
    );
  let messageText =
    ReactDOMRe.Style.make(~fontSize="16px", ~color="rgba(0, 0, 0, 0.4)", ());
  let buttons =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="row",
      ~justifyContent="space-between",
      ~padding="10px",
      ~backgroundColor="#fafafa",
      (),
    );
};

let make =
    (
      ~icon=?,
      ~message=?,
      ~confirmWording,
      ~cancelWording,
      ~onConfirm,
      ~onCancel,
      ~maxWidth=?,
      children,
    ) => {
  ...component,
  render: _self =>
    <div style=Styles.root>
      <div style=Styles.layer />
      <div
        style=(
          ReactDOMRe.Style.combine(
            Styles.container,
            ReactDOMRe.Style.make(
              ~maxWidth=
                switch (maxWidth) {
                | Some(maxWidth) => string_of_int(maxWidth) ++ "px"
                | None => ""
                },
              (),
            ),
          )
        )>
        (
          switch (icon) {
          | Some(icon) => <div style=Styles.icon> icon </div>
          | None => ReasonReact.null
          }
        )
        <div
          style=(
            ReactDOMRe.Style.make(
              ~borderBottom="1px solid rgba(0, 0, 0, 0.1)",
              ~padding="20px 10px",
              ~textAlign=Array.length(children) == 0 ? "center" : "left",
              ~color="rgba(0, 0, 0, 0.4)",
              (),
            )
          )>
          (
            switch (message) {
            | Some(message) =>
              <Text style=Styles.messageText>
                (ReasonReact.string(message))
              </Text>
            | None => ReasonReact.null
            }
          )
          (Array.length(children) != 0 ? children[0] : ReasonReact.null)
        </div>
        <div style=Styles.buttons>
          <Button onPress=onCancel color="#9B9B9B" title=cancelWording />
          <div
            style=(
              ReactDOMRe.Style.make(
                ~width="10px",
                ~height="10px",
                ~flexShrink="0",
                (),
              )
            )
          />
          <Button onPress=onConfirm color="#fb5" title=confirmWording />
        </div>
      </div>
    </div>,
};
