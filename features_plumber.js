// $Id$

/**
 * @file
 * Features Plumber js.
 */

Drupal.behaviors.featuresPlumber = function(context) {
  // By not filtering to context, this will call every time.
  var table = $('#features-export-populated');
  var form = $('#features-plumber-form');

  //form.children().unwrap();
  $('.features-plumber-plumbable', table).each(function () {
    var item = $(this);
    var component = item.attr('component');
    var componentVal = item.attr('component_val');
    $('input[component="' + component + '"][component_val="' + componentVal + '"]', form).prependTo(item);
  });
}