let component = ReasonReact.statelessComponent("Dialog");

module Styles = {
  let root =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="column",
      ~alignItems="center",
      ~justifyContent="flex-start",
      ~padding="40px 10px",
      ~width="100vw",
      ~height="100vh",
      ~boxSizing="border-box",
      (),
    );
  let container =
    ReactDOMRe.Style.make(
      ~backgroundColor="#fff",
      ~borderRadius="4px",
      ~overflow="hidden",
      ~zIndex="0",
      ~boxShadow="0 2px 4px rgba(0, 0, 0, 0.16)",
      ~position="relative",
      ~display="flex",
      ~flexDirection="column",
      (),
    );
  let header =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="row",
      ~alignItems="center",
      ~borderBottom="1px solid rgba(0, 0, 0, 0.1)",
      ~flexShrink="0",
      (),
    );
  let headerText =
    ReactDOMRe.Style.make(
      ~flexGrow="1",
      ~display="flex",
      ~flexDirection="column",
      ~alignItems="flex-start",
      ~minWidth="0",
      ~padding="10px",
      (),
    );
  let headerTitle =
    ReactDOMRe.Style.make(
      ~wordBreak="break-word",
      ~fontSize="16px",
      ~fontWeight="700",
      ~color="rgba(0, 0, 0, 0.4)",
      (),
    );
  let headerDescription =
    ReactDOMRe.Style.make(
      ~wordBreak="break-word",
      ~fontSize="12px",
      ~color="rgba(0, 0, 0, 0.4)",
      (),
    );
  let close = ReactDOMRe.Style.make(~padding="10px", ());
  let closeIcon = ReactDOMRe.Style.make(~opacity="0.4", ());
  let contents =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="column",
      ~flexGrow="1",
      ~overflow="auto",
      (),
    );
};

let defaultUnderlayColor = "rgba(0, 0, 0, 0.3)";

let make =
    (
      ~title,
      ~description=?,
      ~onPressClose,
      ~minWidth=0,
      ~maxWidth=?,
      ~underlayColor=defaultUnderlayColor,
      ~underlayStyle=?,
      children,
    ) => {
  ...component,
  render: _self =>
    <div style=Styles.root>
      <div
        onClick=((_) => onPressClose())
        style=(
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~position="fixed",
              ~top="0",
              ~left="0",
              ~right="0",
              ~bottom="0",
              ~backgroundColor=underlayColor,
              ~transition="background-color .5s ease-in-out",
              (),
            ),
            switch (underlayStyle) {
            | Some(style) => style
            | None => ReactDOMRe.Style.make()
            },
          )
        )
      />
      <div
        style=(
          ReactDOMRe.Style.combine(
            Styles.container,
            ReactDOMRe.Style.make(
              ~minWidth=string_of_int(minWidth) ++ "px",
              ~maxWidth=
                switch (maxWidth) {
                | Some(maxWidth) => string_of_int(maxWidth) ++ "px"
                | None => ""
                },
              (),
            ),
          )
        )>
        <div style=Styles.header>
          <div style=Styles.headerText>
            <Text style=Styles.headerTitle>
              (ReasonReact.string(title))
            </Text>
            (
              switch (description) {
              | Some(description) =>
                <Text style=Styles.headerDescription>
                  (ReasonReact.string(description))
                </Text>
              | None => ReasonReact.null
              }
            )
          </div>
          <TouchableOpacity onPress=onPressClose style=Styles.close>
            <span style=Styles.closeIcon>
              (ReasonReact.string({js|✖️|js}))
            </span>
          </TouchableOpacity>
        </div>
        <div style=Styles.contents> children[0] </div>
      </div>
    </div>,
};
