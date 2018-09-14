let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item: ItemData.item, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div className="item">
      <label>
        <input
          _type="checkbox"
          checked={Js.Boolean.to_js_boolean(item.completed)}
          onChange={_evt => onToggle()}
        />
        {
          let title = item.title;
          ReasonReact.stringToElement({j|todo item $(title)|j});
        }
      </label>
    </div>,
};
