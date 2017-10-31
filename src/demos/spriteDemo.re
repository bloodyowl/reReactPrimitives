module DemoSpriteSheet = {
  let url = "./assets/sprite.png";
  let width = 150;
  let height = 300;
};

module DemoSprite = Sprite.Make(DemoSpriteSheet);

ReactDOMRe.renderToElementWithId(
  <div>
    <DemoSprite width=150 height=150 x=0 y=150 />
    <br />
    <DemoSprite width=150 height=150 x=0 y=0 />
  </div>,
  "root"
);
